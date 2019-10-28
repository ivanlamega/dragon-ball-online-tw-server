CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 227;
	title = 22702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 22708;
				gtype = 1;
				area = 22701;
				goal = 22704;
				grade = 132203;
				rwd = 100;
				sort = 22705;
				stype = 2;
				taid = 1;
				title = 22702;
			}
			CDboTSActNPCConv
			{
				conv = 22709;
				ctype = 1;
				idx = 3142210;
				taid = 2;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 22708;
			gtype = 1;
			oklnk = 2;
			area = 22701;
			goal = 22704;
			sort = 22705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 22702;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 22714;
			nextlnk = 254;
			rwdtbl = 22701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511301;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 22707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 3142210;
			}
			CDboTSCheckLvl
			{
				maxlvl = 14;
				minlvl = 6;
			}
			CDboTSCheckClrQst
			{
				or = "224;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

