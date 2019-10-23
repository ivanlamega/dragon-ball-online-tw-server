CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 521;
	title = 52102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 52107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8032118;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 5;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 52109;
				ctype = 1;
				idx = 8032118;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 52108;
				gtype = 2;
				area = 52101;
				goal = 52104;
				grade = 132203;
				rwd = 100;
				sort = 52105;
				stype = 1;
				taid = 1;
				title = 52102;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSItemIdentity
			{
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 52114;
			nextlnk = 254;
			rwdtbl = 52101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8032118;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 52108;
			gtype = 2;
			oklnk = 2;
			area = 52101;
			goal = 52104;
			sort = 52105;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 52102;
		}
	}
}

