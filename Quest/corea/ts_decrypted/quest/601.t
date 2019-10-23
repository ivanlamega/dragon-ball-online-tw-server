CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 601;
	title = 60102;

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
				cont = 60108;
				gtype = 1;
				area = 60101;
				goal = 60104;
				grade = 132203;
				rwd = 100;
				sort = 60105;
				stype = 2;
				taid = 1;
				title = 60102;
			}
			CDboTSActNPCConv
			{
				conv = 60109;
				ctype = 1;
				idx = 3031205;
				taid = 2;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 60108;
			gtype = 1;
			oklnk = 2;
			area = 60101;
			goal = 60104;
			sort = 60105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 60102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 60114;
			nextlnk = 254;
			rwdtbl = 60101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2972107;
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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 60107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3031205;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
		}
	}
}

