CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1465;
	title = 146502;

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
				conv = 146509;
				ctype = 1;
				idx = 1352101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 146508;
				gtype = 2;
				area = 146501;
				goal = 146504;
				grade = 132203;
				rwd = 100;
				sort = 146505;
				stype = 1;
				taid = 1;
				title = 146502;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 146507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1352101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
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
			cont = 146508;
			gtype = 2;
			oklnk = 2;
			area = 146501;
			goal = 146504;
			sort = 146505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 146502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 146514;
			nextlnk = 254;
			rwdtbl = 146501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1431106;
			}
		}
	}
}

