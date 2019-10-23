CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 735;
	title = 73502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 73509;
				ctype = 1;
				idx = 3032103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 73508;
				gtype = 1;
				area = 73501;
				goal = 73504;
				grade = 132203;
				rwd = 100;
				sort = 73505;
				stype = 2;
				taid = 1;
				title = 73502;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 73514;
			nextlnk = 254;
			rwdtbl = 73501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031201;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 73508;
			gtype = 1;
			oklnk = 2;
			area = 73501;
			goal = 73504;
			sort = 73505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 73502;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 73507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3032103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 33;
				minlvl = 25;
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
	}
}

