CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 667;
	title = 66702;

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
				cont = 66708;
				gtype = 1;
				area = 66701;
				goal = 66704;
				grade = 132203;
				rwd = 100;
				sort = 66705;
				stype = 2;
				taid = 1;
				title = 66702;
			}
			CDboTSActNPCConv
			{
				conv = 66709;
				ctype = 1;
				idx = 3031101;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 66707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckClrQst
			{
				and = "666;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 66708;
			gtype = 1;
			oklnk = 2;
			area = 66701;
			goal = 66704;
			sort = 66705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 66702;
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
			desc = 66714;
			nextlnk = 254;
			rwdtbl = 66701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7132101;
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

