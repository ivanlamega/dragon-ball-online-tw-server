CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6013;
	title = 601302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 601315;
				ctype = 1;
				idx = 7091107;
				taid = 3;
			}
			CDboTSActRegQInfo
			{
				cont = 601308;
				gtype = 1;
				area = 601301;
				goal = 601304;
				grade = -1;
				rwd = 100;
				sort = 601305;
				stype = 8;
				taid = 1;
				title = 601302;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 4073100;
				cnt0 = 2;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 9;
			elnk = 255;
			nextlnk = 10;
			prelnk = "8;";

			CDboTSActETimerS
			{
				sort = 0;
				taid = 1;
				tgid = 1;
				time = 300000;
			}
			CDboTSActWorldPlayScript
			{
				sid = 6013;
				start = 0;
				taid = 2;
				uof = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 6;
			prelnk = "4;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 2000;
			}
		}
		CDboTSContGCond
		{
			cid = 11;
			prelnk = "10;";
			nolnk = 255;
			rm = 0;
			yeslnk = 12;

			CDboTSClickNPC
			{
				npcidx = 3143112;
			}
		}
		CDboTSContGAct
		{
			cid = 10;
			elnk = 255;
			nextlnk = 11;
			prelnk = "9;";

			CDboTSActNPCConv
			{
				conv = 601326;
				ctype = 1;
				idx = 3143112;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 6;
			elnk = 255;
			nextlnk = 7;
			prelnk = "5;";

			CDboTSActNPCConv
			{
				conv = 601320;
				ctype = 1;
				idx = 3143112;
				taid = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSClickNPC
			{
				npcidx = 7091107;
			}
		}
		CDboTSContGAct
		{
			cid = 12;
			elnk = 255;
			nextlnk = 100;
			prelnk = "11;";

			CDboTSActPortal
			{
				dx = "1.000000";
				px = "5491.140137";
				widx = 1;
				dy = "0.000000";
				py = "-129.990005";
				taid = 1;
				type = 0;
				dz = "0.000000";
				pz = "1088.339966";
			}
		}
		CDboTSContGAct
		{
			cid = 7;
			elnk = 253;
			nextlnk = 8;
			prelnk = "6;";

			CDboTSActETimerS
			{
				sort = 0;
				taid = 2;
				tgid = 1;
				time = 300000;
			}
			CDboTSActWorldPlayScript
			{
				sid = 6013;
				start = 1;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "13;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 13;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 8;
			prelnk = "7;";
			nolnk = 255;
			rm = 0;
			yeslnk = 9;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 601314;
			nextlnk = 13;
			rwdtbl = 601301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "12;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7091107;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 601307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7091107;
			}
			CDboTSCheckPCCls
			{
				clsflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6012;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "7;1;0;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 601308;
			gtype = 1;
			oklnk = 2;
			area = 601301;
			goal = 601304;
			sort = 601305;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 601302;
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "3;";

			CDboTSActPortal
			{
				dx = "1.000000";
				px = "-2622.530029";
				widx = 1;
				dy = "0.000000";
				py = "-122.699997";
				taid = 1;
				type = 0;
				dz = "0.000000";
				pz = "-4554.459961";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 1;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
	}
}

