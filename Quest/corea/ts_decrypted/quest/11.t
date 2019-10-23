CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 11;
	title = 1102;

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
				cont = 1108;
				gtype = 0;
				area = 1101;
				goal = 1104;
				grade = 132203;
				rwd = 100;
				sort = 1105;
				stype = 1;
				taid = 1;
				title = 1102;
			}
			CDboTSActNPCConv
			{
				conv = 1109;
				ctype = 1;
				idx = 8411101;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 1114;
			nextlnk = 254;
			rwdtbl = 1101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1111101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 1107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8411101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 11;
				minlvl = 3;
			}
			CDboTSCheckClrQst
			{
				and = "10;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 1108;
			gtype = 0;
			oklnk = 2;
			area = 1101;
			goal = 1104;
			sort = 1105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 1102;
		}
	}
}

